namespace Music.Application.Tracks.Common;

public record RecommendedTrackResult
{
    public RecommendedTrackResult(Guid trackId, string artistName, string trackName)
    {
        TrackId = trackId;
        ArtistName = artistName;
        TrackName = trackName;
    }

    private RecommendedTrackResult()
    {
    }

    public Guid TrackId { get; }

    public string ArtistName { get; }

    public string TrackName { get; }
}