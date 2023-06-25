import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get current user's username
    user = session["user_id"]

    # Select the values in homepage which eventually want to print in buy table
    homepage = db.execute("SELECT price, stock_price_current, SUM(bought) AS total_shares, SUM(price * bought) AS total_amount_in_share, symbol, name FROM history GROUP BY (symbol) HAVING user_id = ? AND total_shares > 0", user)

    # Convert each value to USD
    for data in homepage:
                data["price"] = usd(data["price"])
                data["total_amount_in_share"] = usd(data["total_amount_in_share"])
                data["stock_price_current"] = usd(lookup(data["symbol"])["price"])

    cash = db.execute("SELECT cash FROM users WHERE id =?", user)
    cash_remaining = cash[0]["cash"]

    # Save the value of total value purchased in shares by the person
    total = db.execute("SELECT SUM(price * bought) AS total_amount_in_shares FROM history WHERE user_id = ?", user)
    if total[0]["total_amount_in_shares"] is None:
        total_value = cash_remaining

    else:
        total_value = total[0]["total_amount_in_shares"] + cash_remaining

    total_value = usd(total_value)

    cash_remaining = usd(cash_remaining)

    return render_template("home.html", homepage = homepage, total_value = total_value, cash_remaining = cash_remaining)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # If person enters via post route
    if request.method == "POST":

        quantity = request.form.get("shares")

        # If the user didn't enter name of the company
        if not request.form.get("symbol"):
            return apology("Enter name of the company", 400)

        # If the user didn't enter number of shares
        elif not quantity:
            return apology("Enter the number of shares", 400)

        # If the users did not enter positive shares
        # IF the numbers entered are fractional
        elif  not quantity.isdigit():
            return apology("partial number not allowed", 400)

        elif quantity is None:
            return apology("Value cannot be blank", 400)

        elif quantity == None:
            return apology("Value cannot be blank", 400)


        # If user entered wrong script
        elif lookup(request.form.get("symbol")) == None:
            return apology("invalid script", 400)

        quantity = int(quantity)

        # See which scipt symbol user typed
        symbol = request.form.get("symbol").upper()

        # See name of the stock
        name = lookup(symbol)["name"]

        # Get price of 1 stock user has chosen
        price = lookup(symbol)["price"]

        # Calculating total amount user has requested to buy for
        total_amount = (price) * (quantity)

        # Get current user's username
        user = session["user_id"]

        # Total available cash with user currently
        total_cash_list = db.execute("SELECT cash FROM users WHERE id = ?", user)

        # Convert list into number
        total_cash = total_cash_list[0]["cash"]

        # Cash remaining with the user
        cash_remaining = total_cash - total_amount

        # Calculate the daytime  to store it in table
        now = datetime.now()
        date_time = now.strftime("%m/%d/%Y, %H:%M:%S")

        # If cash remaining is positive, redirect to home page
        if cash_remaining >= 0:

            # Add data into data base
            db.execute("INSERT INTO history (user_id, bought, symbol, name, price, timedate) VALUES (?, ?, ?, ?, ?, ?)", user, quantity, symbol, name, price, date_time)

            # Update the total cash the customer has left
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_remaining, user)

            return redirect("/")

        else:
            return apology("cash negative")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get current user's username
    user = session["user_id"]

    # Select the values in homepage which eventually want to print in buy table
    homepage = db.execute("SELECT price, stock_price_current, bought, symbol, timedate, name FROM history  WHERE user_id = ?", user)

    # Convert each value to USD
    for data in homepage:
                data["price"] = usd(data["price"])

    return render_template("history.html", homepage = homepage)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # If form is submitted via post
    if request.method == "POST":

        #if there is no enry
        if not request.form.get("symbol"):
            return apology("Box cannot be empty", 400)

        # If the symbol doesn't exist
        if lookup(request.form.get("symbol")) == None:
            return apology("This name of script is invalid", 400)

        # save the stock name that client asked the quote for
        symbol = request.form.get("symbol")

        # Name of scipt
        name = lookup(symbol)["name"]

        # Using the lookup function to fetch the price of share
        price = lookup(symbol)["price"]

        # Convert price in USD
        rate = usd(price)

        # Place the value of price in html file
        return render_template("quoted.html", name = name, rate = rate)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    #Forget any user id
    session.clear()

    # User reached route via POST
    if request.method == "POST":

        # Ensure 'Username' is not empty
        if not request.form.get("username"):
            return apology("Userame cant be blank", 400)

        # Ensure 'Password' is not empty
        elif not request.form.get("password"):
            return apology("Password cant be blank", 400)

        # Ensure 'Confirmation' is not empty
        elif not request.form.get("confirmation"):
            return apology("Confirmation cant be blank", 400)

        # Query data for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # If username already exists,
        if len(rows) > 0:
            return apology("Usename already exists", 400)

        # Ensure that confirmation and password are same
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("'Password' and 'Confirmation' should be the same", 400)

        # If username is new, save it in db
        username = request.form.get("username")

        # Save password in db too
        hash = generate_password_hash(request.form.get("password"))

        # Actually saving it in db
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",username, hash)

        # Return to login page
        return redirect("/login")

    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    """Sell shares of stock"""
    if request.method == "POST":

        # User id for future sqlite functions
        user = session["user_id"]

        # Save the input of users in variables
        symbol = request.form.get("symbol")
        quantity = request.form.get("shares")

        if not symbol:
            return apology("must provide stock name", 400)

        if not quantity:
            return apology("must provide quantity of shares", 400)

        # Calculate the daytime  to store it in table
        now = datetime.now()
        date_time = now.strftime("%m/%d/%Y, %H:%M:%S")

        symbol = symbol.upper()

        # Now check if the client has enough shares or not
        homepage = db.execute("SELECT price, stock_price_current, SUM(bought) AS total_shares, SUM(price * bought) AS total_amount_in_share, symbol, name FROM history GROUP BY (symbol) HAVING user_id = ?", user)

        original_shares = db.execute("SELECT SUM(bought) AS total_shares FROM history GROUP BY (symbol) HAVING user_id =? AND symbol = ?", user, symbol)

        if original_shares[0]["total_shares"] - int(quantity) >= 0:

            # Get price of 1 stock user has chosen
            price = lookup(symbol)["price"]

            # See name of the stock
            name = lookup(symbol)["name"]

            # Total available cash with user currently
            cash = db.execute("SELECT cash FROM users WHERE id = ?", user)

            cash_update = cash[0]["cash"] + price * float(quantity)

            # Update the total cash the customer has left
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_update, user)

            quantity = -int(quantity)

            db.execute("INSERT INTO history (user_id, bought, symbol, name, price, timedate) VALUES (?, ?, ?, ?, ?, ?)", user, quantity, symbol, name, price, date_time)

            return redirect("/")

        else:
            return apology("You dont own this share")

    else:
        # User id for future sqlite functions
        user = session["user_id"]

        # Now check if the client has enough shares or not
        homepage = db.execute("SELECT price, stock_price_current, SUM(bought) AS total_shares, SUM(price * bought) AS total_amount_in_share, symbol, name FROM history GROUP BY (symbol) HAVING user_id = ? and total_shares > 0", user)

        return render_template("sell.html", homepage = homepage)


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    if request.method == "POST":

        # User id for future sqlite functions
        user = session["user_id"]

        cash = float(request.form.get("cash"))

        if cash > 0:

            previous_cash = db.execute("SELECT cash FROM users WHERE id = ?", user)

            total_cash = previous_cash[0]["cash"] + cash

            db.execute("UPDATE users SET cash =? WHERE id = ?", total_cash, user)
            return redirect("/")
        else:
            return apology("cannot place -ve value or zero")