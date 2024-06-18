SELECT "ArtistId", "Name", count(*) AS "Followers"
FROM "Artists"
    JOIN public."Followers" F on "Artists"."Id" = F."ArtistId"
GROUP BY F."ArtistId", "Name"
ORDER BY "Followers";