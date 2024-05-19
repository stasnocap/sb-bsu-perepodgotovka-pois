using Music.Domain.Artist.ValueObjects;
using Music.Domain.Common.Models;

namespace Music.Domain.Artist;

public sealed class Artist : AggregateRoot<ArtistId>
{
    public string Name { get; }
    public string CreatedDateTime { get; }
    public string UpdatedDateTime { get; }
    
    private Artist(ArtistId artistId, string name) : base(artistId)
    {
        Name = name;
    }

    public static Artist Create(string name)
    {
        return new(ArtistId.CreateUnique(), name);
    }
}