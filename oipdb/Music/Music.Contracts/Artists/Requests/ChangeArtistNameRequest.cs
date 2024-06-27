namespace Music.Contracts.Artists.Requests;

public record ChangeArtistNameRequest(Guid Id, string Name);