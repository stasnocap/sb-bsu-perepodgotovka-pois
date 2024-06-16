using MediatR;
using Music.Application.Artists.Common;

namespace Music.Application.Artists.Queries.ListArtists;

public record ListArtistsQuery : IRequest<List<ArtistResult>>;