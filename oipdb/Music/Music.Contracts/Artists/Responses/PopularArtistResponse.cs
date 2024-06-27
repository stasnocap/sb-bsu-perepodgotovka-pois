namespace Music.Contracts.Artists.Responses;

public record PopularArtistResponse(Guid ArtistId, string Name, int Followers);