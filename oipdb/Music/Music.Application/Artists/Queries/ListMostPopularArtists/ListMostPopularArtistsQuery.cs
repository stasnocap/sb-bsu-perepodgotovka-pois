using MediatR;
using Music.Application.Artists.Common;

namespace Music.Application.Artists.Queries.ListMostPopularArtists;

public record ListMostPopularArtistsQuery : IRequest<List<PopularArtistResult>>;