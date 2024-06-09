using Music.Domain.Artist.Events;
using Music.Domain.Artist.ValueObjects;
using Music.Domain.Common.Models;

namespace Music.Domain.Artist;

public sealed class Artist : AggregateRoot<ArtistId>
{
    public string Name { get; }
    
    private Artist(ArtistId id, string name) : base(id)
    {
        Name = name;
    }

    public static Artist Create(string name)
    {
        var artist = new Artist(ArtistId.CreateUnique(), name);
        
        artist.AddDomainEvent(new ArtistCreatedDomainEvent(artist));
        
        return artist;
    }
}