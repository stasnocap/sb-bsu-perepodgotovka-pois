namespace Music.Application.Tracks.Common;

public record PopularTrackResult
{
    public PopularTrackResult(Guid trackId, string trackName, int likes)
    {
        TrackId = trackId;
        Likes = likes;
        TrackName = trackName;
    }

    private PopularTrackResult()
    {
    }

    public Guid TrackId { get; init; }
    public int Likes { get; init; }
    public string TrackName { get; init; }
}