SELECT genrename, COUNT(artist_id) 
FROM genre g  
LEFT JOIN artistsgenres ON genre_id  = g.id
GROUP BY genrename
ORDER BY COUNT DESC;

SELECT '1970-2020' AS "release years", COUNT(*)
FROM track WHERE track.album_id IN
(SELECT id FROM album WHERE albumreleASeyear >=1970 AND albumreleASeyear <=2000);

SELECT a.albumname , ROUND(CAST (AVG(duration) AS numeric), 2 ) AS "Average track time" 
FROM track t LEFT JOIN album a ON t.album_id = a.id GROUP BY album_id, a.albumname;

SELECT artistname AS "Not released albums in 2000" FROM artist 
WHERE id IN
(SELECT DISTINCT artist_id FROM artistsalbums  WHERE artist_id IN 
(SELECT id FROM album WHERE albumreleaseyear != 2000));

SELECT collectionname FROM collection WHERE id IN 
(SELECT DISTINCT collection_id FROM trackscollections WHERE track_id IN
	(SELECT id FROM track WHERE album_id IN 
		(SELECT album_id FROM artistsalbums WHERE artist_id in 
			(SELECT id FROM artist WHERE artistname = 'The Bugs')
		)
	)
);

