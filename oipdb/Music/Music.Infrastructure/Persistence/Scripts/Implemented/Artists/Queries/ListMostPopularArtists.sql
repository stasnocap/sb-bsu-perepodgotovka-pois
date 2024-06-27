SELECT "ArtistId", "Name", count(*) AS "Followers"
FROM "Artists" A
    JOIN "Followers" F on A."Id" = F."ArtistId"
GROUP BY F."ArtistId", "Name"
ORDER BY "Followers";