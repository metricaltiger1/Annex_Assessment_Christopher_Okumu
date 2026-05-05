-- Question 2: Top Scoring Students (SQL)
-- Problem Statement
-- Write a SQL query to retrieve the ID and NAME of the three highest-scoring students, sorted by score in descending order. For students with matching scores, sort by ID in ascending order.

-- Schema
-- STUDENT Table:

-- Column	Type	Description
-- ID	Integer	Unique ID (Primary Key)
-- NAME	String	Student name
-- SCORE	Float	Math score
-- Sample Input
-- ID	NAME	SCORE
-- 1	Bob	50.0
-- 2	John	65.5
-- 3	Harry	45.0
-- 4	Dick	85.0
-- 5	Dev	25.0
-- 6	Sid	98.0
-- 7	Tom	90.0
-- 8	Julia	70.5
-- 9	Erica	81.0
-- 10	Jerry	85.0
-- Expected Output
-- ID	NAME
-- 6	Sid
-- 7	Tom
-- 4	Dick

SELECT ID, NAME FROM STUDENT ORDER BY SCORE DESC, ID ASC LIMIT 3;

