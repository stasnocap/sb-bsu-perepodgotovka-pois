<%@ Page Language="C#" %>

<html>
<body>
<form id="form1" runat="server">
    Нами принята следующая информация о Вас:<br><br>
    <ul>
        <%
            Response.Write($@"
                <li>Фамилия: {Request["Family"]}</li>
                <li>Имя: {Request["Name"]}</li>
                <li>Отчество: {Request["Patronymic"]}</li>
                <li>Пасспорт: {Request["Passport"]}</li>
                <li>Адрес: {Request["Address"]}</li>
                <li>Телефон: {Request["Telephone"]}</li>
                <li>Сумма: {Request["Sum"]}</li>
            ");
        %>
    </ul>
    Спасибо! Ваши данные приняты!
</form>
</body>
</html>