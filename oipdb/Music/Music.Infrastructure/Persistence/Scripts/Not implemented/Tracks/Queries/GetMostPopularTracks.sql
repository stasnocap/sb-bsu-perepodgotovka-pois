SELECT "TrackId", "Name", count(*) AS "Likes"
FROM get_tracks() T
         JOIN public."LikedTracks" LT on T."Id" = LT."TrackId"
GROUP BY "TrackId", "Name"
ORDER BY "Likes";
