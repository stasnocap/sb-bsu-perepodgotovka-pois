using ClockServer;
using CoreRemoting;

namespace TimeServer;

public class Stopwatch : IStopwatch
{
    private readonly Dictionary<Guid, System.Diagnostics.Stopwatch> Stopwatches = new();

    public void Start()
    {
        var sessionId = RemotingSession.Current.SessionId;

        var stopwatch = new System.Diagnostics.Stopwatch();
        stopwatch.Start();

        Stopwatches[sessionId] = stopwatch;
    }

    public long Stop()
    {
        var sessionId = RemotingSession.Current.SessionId;

        if (!Stopwatches.TryGetValue(sessionId, out var stopwatch))
        {
            return -1;
        }

        stopwatch.Stop();
        return stopwatch.ElapsedMilliseconds;
    }
}