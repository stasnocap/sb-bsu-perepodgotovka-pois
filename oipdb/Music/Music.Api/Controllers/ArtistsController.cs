using Microsoft.AspNetCore.Mvc;

namespace Music.Api.Controllers;

[Route("[controller]")]
public class ArtistsController: ApiController
{
    [HttpGet]
    public IActionResult ListArtists()
    {
        return Ok(Array.Empty<string>());
    }
}