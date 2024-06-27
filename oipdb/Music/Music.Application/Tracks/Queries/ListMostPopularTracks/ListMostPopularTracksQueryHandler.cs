using MediatR;
using Music.Application.Common.Interfaces.Persistence;
using Music.Application.Tracks.Common;

namespace Music.Application.Tracks.Queries.ListMostPopularTracks;

public class ListMostPopularTracksQueryHandler(ITrackRepository _trackRepository) : IRequestHandler<ListMostPopularTracksQuery, List<PopularTrackResult>>
{
    public async Task<List<PopularTrackResult>> Handle(ListMostPopularTracksQuery request, CancellationToken cancellationToken)
    {
        var result = await _trackRepository.ListMostPopularTracksAsync(cancellationToken);

        return result;
    }
}