<html>
  <head>
    <style>
    <!--
      body { font: 10pt verdana }
      table { font: 10pt verdana }
      input { font: 10pt verdana }
    -->
    </style>
  </head>
  <body>
    <table cellpadding="4" border="1">
      <tr bgcolor="yellow">
        <td>
Здравствуйте!
        </td>
      </tr>
    </table>
    <h3>Ваши реквизиты:</h3>
    <form runat="server">
      <table cellpadding="4">
        <tr>
          <td align="right">
            Фамилия
          </td>
          <td>
            <asp:TextBox ID="Family" RunAt="server" />
          </td>
          <td>
            <asp:RequiredFieldValidator
              ControlToValidate="Family"
              ErrorMessage="Пожалуйста, введите Вашу фамилию"
              Display="dynamic"
              RunAt="server"
            />
          </td>
        </tr>
        <tr>
          <td align="right">
            Имя
          </td>
          <td>
            <asp:TextBox ID="Name" RunAt="server" />
          </td>
          <td>
            <asp:RequiredFieldValidator
              ControlToValidate="Name"
              ErrorMessage="Пожалуйста, введите Вашу имя"
              Display="dynamic"
              RunAt="server"
            />
          </td>
        </tr>
        <tr>
          <td align="right">
            Отчество
          </td>
          <td>
            <asp:TextBox ID="Patronymic" RunAt="server" />
          </td>
          <td>
            <asp:RequiredFieldValidator
              ControlToValidate="Patronymic"
              ErrorMessage="Пожалуйста, введите Ваше отчество"
              Display="dynamic"
              RunAt="server"
            />
          </td>
        </tr>
        <tr>
          <td align="right">
            Номер паспорта
          </td>
          <td>
            <asp:TextBox ID="Passport" RunAt="server" />
          </td>
          <td>
            <asp:RequiredFieldValidator
              ControlToValidate="Passport"
              ErrorMessage="Пожалуйста, введите Ваш паспорт"
              Display="dynamic"
              RunAt="server"
            />
          </td>
        </tr>
        <tr>
          <td align="right">
            Адрес
          </td>
          <td>
            <asp:TextBox ID="Address" RunAt="server" />
          </td>
          <td>
            <asp:RequiredFieldValidator
              ControlToValidate="Address"
              ErrorMessage="Пожалуйста, введите Ваш адрес"
              Display="dynamic"
              RunAt="server"
            />
          </td>
        </tr>
        <tr>
          <td align="right">
            Телефон
          </td>
          <td>
            <asp:TextBox ID="Telephone" RunAt="server" />
          </td>
          <td>
            <asp:RequiredFieldValidator
              ControlToValidate="Telephone"
              ErrorMessage="Пожалуйста, введите Ваш телефон"
              Display="dynamic"
              RunAt="server"
            />
          </td>
        </tr>
        <tr>
          <td align="right">
            Сумма
          </td>
          <td>
            <asp:TextBox ID="Sum" RunAt="server" />
          </td>
          <td>
            <asp:RequiredFieldValidator
              ControlToValidate="Sum"
              ErrorMessage="Пожалуйста, введите сумму предполагаемого кредита"
              Display="dynamic"
              RunAt="server"
            />
          </td>
        </tr>
        <tr>
          <td>
          </td>
          <td>
            <asp:Button Text="Отправить заявку" OnClick="OnSignMeUp"
              RunAt="server" />
          </td>
          <td>
              
          </td>
        </tr>
      </table>
    </form>
  </body>
</html>

<script language="C#" runat="server">
  void OnSignMeUp (Object sender, EventArgs e)
  {
      if (IsValid) {
          Response.Redirect ($"ThanksForLoan.aspx?Name={Name.Text}&Family={Family.Text}&Patronymic={Patronymic.Text}&Passport={Passport.Text}&Address={Address.Text}&Telephone={Telephone.Text}&Sum={Sum.Text}");
      }
  }
</script>