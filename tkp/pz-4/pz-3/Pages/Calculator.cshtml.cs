using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using pz_3.Models;

namespace pz_3.Pages;

public class CalculatorModel : PageModel
{
    [BindProperty] 
    public Calculator Calculator { get; set; } = null!;
    
    public IActionResult OnGet()
    {
        Calculator = new Calculator();
        return Page();
    }
    
    public IActionResult OnPost()
    {
        if (!ModelState.IsValid)
        {
            return Page();
        }
        
        Calculator.Calculate();

        return Page();
    }
}