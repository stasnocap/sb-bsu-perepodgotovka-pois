<!DOCTYPE html>
<html>
<head>
    <title>Multiplication Table</title>
    <style>
        table {
            width: 50%;
            border-collapse: collapse;
        }
        table, th, td {
            border: 1px solid black;
        }
        th, td {
            padding: 10px;
            text-align: center;
        }
        .even {
            background-color: #add8e6;
        }
    </style>
</head>
<body>
    <h2>Multiplication Table</h2>
    <table>
        <tr>
            <th>&times;</th>
            <?php for ($i = 1; $i <= 10; $i++): ?>
                <th><?php echo $i; ?></th>
            <?php endfor; ?>
        </tr>
        <?php for ($i = 1; $i <= 10; $i++): ?>
            <tr>
                <th><?php echo $i; ?></th>
                <?php for ($j = 1; $j <= 10; $j++): ?>
                    <?php $product = $i * $j; ?>
                    <td class="<?php echo ($product % 2 == 0) ? 'even' : ''; ?>">
                        <?php echo $product; ?>
                    </td>
                <?php endfor; ?>
            </tr>
        <?php endfor; ?>
    </table>
</body>
</html>
