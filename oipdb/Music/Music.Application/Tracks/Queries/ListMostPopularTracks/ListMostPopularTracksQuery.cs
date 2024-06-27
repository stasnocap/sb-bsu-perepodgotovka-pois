using MediatR;
using Music.Application.Tracks.Common;

namespace Music.Application.Tracks.Queries.ListMostPopularTracks;

public class ListMostPopularTracksQuery : IRequest<List<PopularTrackResult>>;