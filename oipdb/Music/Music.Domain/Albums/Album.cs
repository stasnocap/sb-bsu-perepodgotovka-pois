using Music.Domain.Albums.ValueObjects;
using Music.Domain.Common.Models;

namespace Music.Domain.Albums;

public class Album : AggregateRoot<AlbumId>
{
    protected Album(AlbumId id) : base(id)
    {
    }
}