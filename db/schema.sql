-- PostgreSQL runs this file once, when the database is still empty.
-- After a change, delete the database: `docker compose down --volumes`.

-- Example table. Replace it with the first real table.
CREATE TABLE example (
    id integer GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    message text NOT NULL
);

INSERT INTO example (message) VALUES ('Hallo uit PostgreSQL');
