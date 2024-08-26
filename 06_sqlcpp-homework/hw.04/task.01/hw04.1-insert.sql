INSERT INTO artist (artistname)
VALUES	('Avaldi'), 
		('Pelvis Resly'), 
		('AC/HV'), 
		('The Bugs');

INSERT INTO genre (genrename) 
VALUES  ('Classical'),
		('Rock'),
		('Metal'),
		('Pop');
		
INSERT INTO album (albumname, albumreleaseyear) 
VALUES  ('Classics', 1840),
		('Stone', 1960),
		('Rust', 1980),
		('Burst', 2000);

INSERT INTO track ( album_id , tracktitle , duration )
values 	((select id from album where albumname = 'Classics'),'Winter', 5.70),
		((select id from album where albumname = 'Classics'),'Summer', 6.40),
		((select id from album where albumname = 'Stone'),'Around the Dock', 3.30),
		((select id from album where albumname = 'Stone'),'Starman', 5.20),
		((select id from album where albumname = 'Rust'),'My Fate', 3.80),		
		((select id from album where albumname = 'Rust'),'Alley to Hell', 4.30),
		((select id from album where albumname = 'Rust'),'Boomstick', 3.50),
		((select id from album where albumname = 'Burst'),'ClownFace', 3.20),
		((select id from album where albumname = 'Burst'),'GonnaGetUs', 2.50),
		((select id from album where albumname = 'Burst'),'Tell my mom', 2.90);

insert into collection (collectionname, releaseyear)
values 	('Best of Legends', 2011),
		('Drive Fest', 2018),
		('Radio Hits', 2005),
		('School days', 2020);
		
insert into artistsgenres (genre_id, artist_id)
values	((select id from genre where genrename = 'Classical'),(select id from artist where artistname = 'Avaldi')),
		((select id from genre where genrename = 'Rock'),(select id from artist where artistname = 'Pelvis Resly')),
		((select id from genre where genrename = 'Rock'),(select id from artist where artistname = 'AC/HV')),
		((select id from genre where genrename = 'Metal'),(select id from artist where artistname = 'AC/HV')),
		((select id from genre where genrename = 'Rock'),(select id from artist where artistname = 'The Bugs')),
		((select id from genre where genrename = 'Pop'),(select id from artist where artistname = 'The Bugs'));
		
insert into artistsalbums (album_id, artist_id)
values	((select id from album where albumname = 'Classics'),(select id from artist where artistname = 'Avaldi')),
		((select id from album where albumname = 'Stone'),(select id from artist where artistname = 'Pelvis Resly')),
		((select id from album where albumname = 'Rust'),(select id from artist where artistname = 'AC/HV')),
		((select id from album where albumname = 'Burst'),(select id from artist where artistname = 'The Bugs'));
	
insert into trackscollections (track_id, collection_id)
values	((select id from track where tracktitle = 'Winter'),(select id from collection  where collectionname = 'Best of Legends')),
		((select id from track where tracktitle = 'Around the Dock'),(select id from collection  where  collectionname  = 'Best of Legends')),
		((select id from track where tracktitle = 'Alley to Hell'),(select id from collection  where  collectionname  = 'Best of Legends')),
		((select id from track where tracktitle = 'Starman'),(select id from collection  where  collectionname  = 'Drive Fest')),
		((select id from track where tracktitle = 'GonnaGetUs'),(select id from collection  where  collectionname  = 'Drive Fest')),
		((select id from track where tracktitle = 'My Fate'),(select id from collection  where  collectionname  = 'Drive Fest')),
		((select id from track where tracktitle = 'ClownFace'),(select id from collection  where  collectionname  = 'Radio Hits')),
		((select id from track where tracktitle = 'Around the Dock'),(select id from collection  where  collectionname  = 'Radio Hits')),
		((select id from track where tracktitle = 'Summer'),(select id from collection  where  collectionname  = 'Radio Hits')),
		((select id from track where tracktitle = 'Starman'),(select id from collection  where  collectionname  = 'School days')),		
		((select id from track where tracktitle = 'Boomstick'),(select id from collection  where  collectionname  = 'School days')),
		((select id from track where tracktitle = 'Tell my mom'),(select id from collection  where  collectionname  = 'School days')),
		((select id from track where tracktitle = 'Alley to Hell'),(select id from collection  where  collectionname  = 'School days'));
		