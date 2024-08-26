CREATE TABLE IF NOT EXISTS artist (
	id serial PRIMARY KEY ,
	artistname varchar(60) NOT NULL
);

CREATE TABLE IF NOT EXISTS genre (
	id serial PRIMARY KEY ,
	genrename varchar(60) NOT NULL
);

CREATE TABLE IF NOT EXISTS album (
	id serial PRIMARY KEY , 
	albumname varchar(60) ,
	albumreleaseyear int NOT NULL
);

CREATE TABLE IF NOT EXISTS collection (
	id serial PRIMARY KEY ,
	collectionname varchar(60) NOT NULL,
	releaseyear int NOT NULL
);

CREATE TABLE IF NOT EXISTS track (
	id serial PRIMARY KEY ,
	tracktitle varchar(60) NOT NULL,
	duration int NOT NULL,
	album_id int NOT NULL REFERENCES album(id)
);

CREATE TABLE IF NOT EXISTS trackscollections (
	id serial PRIMARY KEY,
	track_id int NOT NULL REFERENCES track(id),
	collection_id int NOT NULL REFERENCES collection(id)
);	

CREATE TABLE IF NOT EXISTS artistsgenres (
	id serial PRIMARY KEY,
	genre_id int NOT NULL REFERENCES genre(id),
	artist_id int NOT NULL REFERENCES artist(id)
);

CREATE TABLE IF NOT EXISTS artistsalbums (
	id serial PRIMARY KEY,
	album_id int NOT NULL REFERENCES album(id),
	artist_id int NOT NULL REFERENCES artist(id)
);