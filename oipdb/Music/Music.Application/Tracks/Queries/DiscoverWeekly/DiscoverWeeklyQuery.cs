using MediatR;
using Music.Application.Tracks.Common;
using Music.Application.Tracks.Queries.ListRecommendedTracks;

namespace Music.Application.Tracks.Queries.DiscoverWeekly;

public class DiscoverWeeklyQuery : IRequest<List<RecommendedTrackResult>>;