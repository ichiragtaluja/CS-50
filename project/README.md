# Stockks
#### Video Demo:  https://youtu.be/O5kYauUIyvs
## Overview:

As a student in the CS50 course, I am excited to present my final project, a web-based simulation of the stock market called CS50 Finance. This platform allows users to buy and sell stocks in real-time using a virtual portfolio, and track their portfolio's performance over time.

To create this project, I used a variety of technical files and programming languages. Below, I will provide an overview of the most important ones.

## Description:

### HTML and CSS

The front-end of the CS50 Finance website was built using HTML and CSS. HTML (HyperText Markup Language) is a standard markup language used to create web pages, and CSS (Cascading Style Sheets) is a stylesheet language used to describe the look and formatting of a document written in HTML.

I used HTML to structure the content of the website, including the layout of the homepage, the login and registration forms, and the various pages for buying and selling stocks and viewing portfolio information. I also used HTML to add interactive elements such as buttons and dropdown menus.

CSS was used to style the website, including the colors, fonts, and overall layout. I created separate CSS files for different sections of the website, such as the homepage, the login and registration forms, and the portfolio pages. This allowed me to easily make changes to the styling of the website without affecting other parts of the code.

All the files in template are html. All the CSS files in static folder

### SQLITE 3

I made 2 tables.

    1) USERS

    2) HISTORY


First table only contains information related to user name and password. Second take has information about each users id and stock buying ad selling data including the likes of time and day of purchase.

### Flask

All the backened work is done in flask. I used Python to write the server-side logic for the website, including the logic for handling user accounts, managing the virtual portfolio, and interacting with the stock market API. I also used Python to connect to a database and store user data, portfolio data, and stock data.

Flask was used to route HTTP requests and handle responses, as well as to render HTML templates and pass data between the server and the client. I used Jinja, a templating engine included with Flask, to embed Python code in the HTML templates and create dynamic pages.















## Tech Stack

**Client:** HTML, CSS, Bootsrap

**Server:** Python, Flask, Sqlite3


## Features

- Real-time market data: See the latest prices and market movements for stocks in your portfolio.
- Stock quotes: Look up the current price and other relevant information for any publicly traded company.


## Demo

Here is a demo video that take you through the usage of the website.

https://youtu.be/O5kYauUIyvs

## About CS50
CS50 is a openware course from Havard University and taught by David J. Malan

Introduction to the intellectual enterprises of computer science and the art of programming. This course teaches students how to think algorithmically and solve problems efficiently. Topics include abstraction, algorithms, data structures, encapsulation, resource management, security, and software engineering. Languages include C, Python, and SQL plus students’ choice of: HTML, CSS, and JavaScript (for web development).

Thank you for all CS50.

Where I get CS50 course? https://cs50.harvard.edu/x/2022/
