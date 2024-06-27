namespace Music.Contracts.Tracks.Responses;

public record PopularTrackResponse(Guid TrackId, string TrackName, int Likes);