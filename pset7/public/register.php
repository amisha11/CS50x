<?php
    // configuration
    require("../includes/config.php");
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
    
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide a password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        else if ($_POST["confirmation"] != $_POST["password"])
        {
            apologize("The password and it's confirmation doesn't match.");
        }
        
        // Fail-safe - check if the user already exists
        $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);
        
        // if we found user, check password
        if (count($rows) == 1)
        {
            apologize("Specified username already exists.");
        }
        else
        {
            // Register the user
            query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
            
            if ($query === false)
            {
                apologize("Could not register user.");
            }
            else
            {
                // Remember the session and redirect
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                
                if (count($rows) == 1)
                {
                    $id = $rows[0]["id"];
                    
                    $_SESSION["id"] = $id;
                    
                    // remember username and current deposit
                    $_SESSION["username"] = $row["username"];
                    $_SESSION["cash"] = $row["cash"];
                    
                    redirect("/");
                }
            }
        }
        
        
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
?>
