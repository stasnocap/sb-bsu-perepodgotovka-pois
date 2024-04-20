// See https://aka.ms/new-console-template for more information

using Dapper;
using Npgsql;

var connectionString = "Host=localhost;Username=postgres;Password=postgres;Database=Music";

List<Artist> artists;
using (var connection = new NpgsqlConnection(connectionString))
{
    const string sql = $"""
                        SELECT
                            ar."{nameof(Artist.Id)}",
                            ar."{nameof(Artist.Name)}",
                            a."{nameof(Album.Id)}",
                            a."{nameof(Album.ArtistId)}",
                            a."{nameof(Album.Name)}",
                            t."{nameof(Track.Id)}",
                            t."{nameof(Track.AlbumId)}",
                            t."{nameof(Track.ArtistId)}",
                            t."{nameof(Track.Name)}"
                        FROM "Tracks" t
                        JOIN "Albums" a on t."AlbumId" = a."Id"
                        JOIN "Artists" ar on t."ArtistId" = ar."Id"
                        """;

    artists = connection
        .Query<Artist, Album, Track, Artist>(sql, map: (artist, album, track) =>
        {
            album.AddTrack(track);
            artist.AddAlbum(album);
            return artist;
        })
        .ToList();
}

foreach (Artist artist in artists)
{
    Console.WriteLine(artist);
}

public abstract class Entity
{
    public long Id { get; init; }

    protected Entity(long id)
    {
        Id = id;
    }

    protected Entity()
    {
    }
}

public class Artist : Entity
{
    public string Name { get; } = string.Empty;

    private readonly List<Album> _albums = [];
    public IReadOnlyList<Album> Albums => _albums;

    public Artist(string name)
    {
        Name = name;
    }

    private Artist()
    {
    }

    public void AddAlbum(Album album)
    {
        _albums.Add(album);
    }
}

public class Album : Entity
{
    public long ArtistId { get; }

    public string Name { get; } = string.Empty;

    private readonly List<Track> _tracks = [];
    
    public IReadOnlyList<Track> Tracks => _tracks;

    public Album(string name, long artistId)
    {
        Name = name;
        ArtistId = artistId;
    }

    private Album()
    {
    }
    
    public void AddTrack(Track track)
    {
        _tracks.Add(track);
    }
}

public class Track : Entity
{
    public long AlbumId { get; }
    
    public long ArtistId { get; }
    
    public string Name { get; } = string.Empty;

    public Track(string name, long albumId, long artistId)
    {
        Name = name;
        AlbumId = albumId;
        ArtistId = artistId;
    }

    private Track()
    {
    }
}