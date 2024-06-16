namespace Music.Contracts.Artists;

public record ChangeArtistNameRequest(Guid Id, string Name);