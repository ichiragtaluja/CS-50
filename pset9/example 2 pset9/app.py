from flask import Flask, render_template, request, redirect
from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///froshims.db")

SPORTS = [
    "Basketball",
    "Cricket",
    "Football"
]

@app.route("/")
def index():
    return render_template("index.html",sports = SPORTS)

@app.route("/deregister", methods=["POST"])
def deregister():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")

@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
        return render_template("failure.html")

    sport = request.form.get("sport")
    if not sport:
        return render_template("failure.html")

    if sport not in SPORTS:
        return render_template("failure.html")

    db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)
    return redirect ("/registrants")

@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT * from registrants")
    return render_template("registrants.html", registrants=registrants)

