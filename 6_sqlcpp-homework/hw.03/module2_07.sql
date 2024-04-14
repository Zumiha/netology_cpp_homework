SELECT estate_object_id, object_type_id, year_of_construction, number_of_rooms
FROM estate_object
WHERE number_of_rooms = 4 AND((object_type_id = 2 AND year_of_construction = 2005) OR (object_type_id = 4 AND year_of_construction BETWEEN 2001 AND 2003))