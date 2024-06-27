using MediatR;
using Music.Application.Artists.Common;
using Music.Domain.Artists.ValueObjects;

namespace Music.Application.Artists.Queries.FansAlsoLikeArtists;

public record FansAlsoLikeArtistsQuery(ArtistId ArtistId) : IRequest<List<FansAlsoLikeArtistResult>>;