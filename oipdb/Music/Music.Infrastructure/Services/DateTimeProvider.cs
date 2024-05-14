using Music.Application.Common.Interfaces.Services;

namespace Music.Infrastructure.Services;

public class DateTimeProvider : IDateTimeProvider
{
    public DateTime UtcNow => DateTime.UtcNow;
}