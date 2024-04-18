SELECT tracktitle, duration FROM track 
WHERE duration = (SELECT MAX (duration) FROM track)
ORDER BY tracktitle ;

SELECT tracktitle, duration FROM track 
WHERE duration >= 3.5
ORDER BY duration DESC;

SELECT collectionname, releaseyear  FROM collection
WHERE releaseyear BETWEEN  2018 AND  2020
ORDER BY collectionname;

SELECT artistname  FROM artist
WHERE artistname NOT LIKE '% %';

SELECT tracktitle  FROM track
WHERE LOWER(tracktitle) LIKE '%my%' OR tracktitle LIKE '%мой%';