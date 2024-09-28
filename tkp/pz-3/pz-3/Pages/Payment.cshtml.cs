using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using pz_3.Models;

namespace pz_3.Pages;

public class PaymentModel : PageModel
{
    [BindProperty] 
    public Payment Payment { get; set; } = null!;
    
    public IActionResult OnGet()
    {
        Payment = new Payment
        {
            Principal = 100_000,
            Rate = 10,
            Term = 240
        };
        return Page();
    }
    
    public IActionResult OnPost()
    {
        if (!ModelState.IsValid)
        {
            return Page();
        }
        
        Payment.Calculate();

        return Page();
    }
}