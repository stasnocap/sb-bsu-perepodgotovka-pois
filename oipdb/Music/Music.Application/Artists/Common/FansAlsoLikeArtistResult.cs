namespace Music.Application.Artists.Common;

public record FansAlsoLikeArtistResult
{
    public FansAlsoLikeArtistResult(Guid artistId, string artistName)
    {
        ArtistId = artistId;
        ArtistName = artistName;
    }

    private FansAlsoLikeArtistResult()
    {
    }
        
    public Guid ArtistId { get; }

    public string ArtistName { get; }
}