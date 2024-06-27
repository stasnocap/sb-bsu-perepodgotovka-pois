using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using Microsoft.AspNetCore.Http;
using Music.Application.Common.Interfaces.Services;
using Music.Domain.Users.ValueObjects;

namespace Music.Infrastructure.Services;

public class UserContext(IHttpContextAccessor _httpContextAccessor) : IUserContext
{
    public UserId GetCurrentUserId() => UserId.Create(Guid.Parse(_httpContextAccessor.HttpContext?.User.FindFirstValue(ClaimTypes.NameIdentifier)!));
}