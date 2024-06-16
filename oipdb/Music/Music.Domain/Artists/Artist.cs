using Music.Domain.Artists.Events;
using Music.Domain.Artists.ValueObjects;
using Music.Domain.Common.Models;

namespace Music.Domain.Artists;

public sealed class Artist : AggregateRoot<ArtistId>
{
    public Name Name { get; private set; }
    
    private Artist(ArtistId id, Name name) : base(id)
    {
        Name = name;
    }

    public void ChangeName(Name name)
    {
        Name = name;
    }

    public static Artist Create(Name name)
    {
        var artist = new Artist(ArtistId.CreateUnique(), name);
        
        artist.AddDomainEvent(new ArtistCreatedDomainEvent(artist));
        
        return artist;
    }
}