using MediatR;
using Music.Application.Tracks.Common;

namespace Music.Application.Tracks.Queries.ListRecommendedTracks;

public record ListRecommendedTracksQuery : IRequest<List<RecommendedTrackResult>>;