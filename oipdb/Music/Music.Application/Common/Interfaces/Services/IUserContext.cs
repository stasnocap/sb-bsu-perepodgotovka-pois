using Music.Domain.Users.ValueObjects;

namespace Music.Application.Common.Interfaces.Services;

public interface IUserContext
{
    UserId GetCurrentUserId();
}