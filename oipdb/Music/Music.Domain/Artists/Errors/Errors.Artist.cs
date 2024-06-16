using ErrorOr;

namespace Music.Domain.Artists.Errors;

public static class Errors
{
    public static class Artist
    {
        public static readonly Error NotFound = Error.NotFound("Artist.NotFound", "Artist with such id was not found.");
        public static readonly Error AlreadyExists = Error.Conflict("Artist.AlreadyExists", "Artist with such name already exists.");
    }
}