-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Event took place on July 28, 2021 and it took place on Humphrey Street

-- So, lets search in crime report
SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2021 AND street = "Humphrey Street";

-- WE now also know that
-- time: 10:15am
-- location of theft: Humphrey Street Bakery
-- date: 28th July 2021
-- thief left the car on street within 10 minutes of the crime *done*
-- thief was widhdrawing money from atm on Leggett Street *done*
-- thief called someone for less than a minute as he was leaving the bakery. *done*
-- They will take earlieast flight on 29 july 2021 from fiftyville
-- other person purchased flight tickets

--list of suspencts who left the bakery within 10 minutes of theft

SELECT * FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 and minute <= 25);

-- id   |  name   |  phone_number  | passport_number | license_plate |
--+--------+---------+----------------+-----------------+---------------+
--| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
--| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
--| 325548 | Brandon | (771) 555-6667 | 7874488539      | R3G7486       |
--| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
--| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
--| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
--| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
--| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 745650 | Sophia  | (027) 555-1068 | 3642612721      | 13FNH73

-- Suspected people based on atm transaction

SELECT name FROM people WHERE id IN ( SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 and year = 2021 AND atm_location = "Leggett Street"));

--   id   |  name   |  phone_number  | passport_number | license_plate |
--+--------+---------+----------------+-----------------+---------------+
--| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
--| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
--| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
--| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
--| 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
--| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
--| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449

--common names from both first and second clues

SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 and minute <= 25) AND name IN (SELECT name FROM people WHERE id IN ( SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 and year = 2021 AND atm_location = "Leggett Street")));

--id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
--| 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
--| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X

--common names after applying filter for phonecall condition

SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND
month = 7 AND year = 2021 AND hour = 10 and minute <= 25) AND name
IN (SELECT name FROM people WHERE id IN ( SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 and year = 2021
AND atm_location = "Leggett Street"))) AND name IN( SELECT name FROM people WHERE phone_number IN (SELECT caller FROM  phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration <= 60));

---------+-------+----------------+-----------------+--------------
--|   id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
--+--------+-------+----------------+-----------------+---------------+

-- flights taken by these two people

SELECT * from passengers WHERE passport_number IN (SELECT passport_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND
month = 7 AND year = 2021 AND hour = 10 and minute <= 25) AND name
IN (SELECT name FROM people WHERE id IN ( SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 and year = 2021
AND atm_location = "Leggett Street"))) AND name IN( SELECT name FROM people WHERE phone_number IN
(SELECT caller FROM  phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration <= 60)));

-- flight_id | passport_number | seat |
--+-----------+-----------------+------+
--| 18        | 3592750733      | 4C   |
--| 24        | 3592750733      | 2C   |
--| 36        | 5773159633      | 4A   |
--| 54        | 3592750733      | 6C   |
--+-----------+-----------------+------+

-- Flight taking off on 29th
SELECT id FROM flights WHERE day = 29 AND year = 2021 AND month = 7
AND origin_airport_id = (SELECT id  FROM airports WHERE city = "Fiftyville");

-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
--| 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
--| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
--| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
--| 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |


-- commonality between both subsets
-- that is flight left on 8th from fiftyville and passport holders were there too
