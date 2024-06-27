namespace Music.Contracts.Tracks.Responses;

public record RecommendedTrackResponse(Guid TrackId, string ArtistName, string TrackName);