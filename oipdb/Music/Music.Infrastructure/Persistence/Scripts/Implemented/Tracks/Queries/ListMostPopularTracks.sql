SELECT "TrackId", "Name", count(*) AS "Likes"
FROM "Tracks" T
         JOIN public."LikedTracks" LT on T."Id" = LT."TrackId"
GROUP BY "TrackId", "Name"
ORDER BY "Likes";
