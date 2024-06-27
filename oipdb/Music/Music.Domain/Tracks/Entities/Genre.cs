using Music.Domain.Common.Models;
using Music.Domain.Tracks.ValueObjects;

namespace Music.Domain.Tracks.Entities;

public class Genre : Entity<GenreId>
{
    private Genre(GenreId id) : base(id)
    {
    }
}