SELECT "TrackId", "AlbumId", "Name", count(*) AS "Likes"
FROM "Tracks"
         JOIN public."LikedTracks" LT on "Tracks"."Id" = LT."TrackId"
GROUP BY "TrackId", "AlbumId", "Name"
ORDER BY "Likes";