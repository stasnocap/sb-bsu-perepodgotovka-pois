namespace Music.Application.Artists.Common;

public record PopularArtistResult
{
    public PopularArtistResult(Guid artistId, string name, int followers)
    {
        ArtistId = artistId;
        Name = name;
        Followers = followers;
    }

    private PopularArtistResult()
    {
    }

    public Guid ArtistId { get; init; }
    public string Name { get; init; }
    public int Followers { get; init; }
}