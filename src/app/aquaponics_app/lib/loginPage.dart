import 'package:flutter/material.dart'; 
import 'package:shared_preferences/shared_preferences.dart';
// PAGES
import 'package:aquaponics_app/homePage.dart';

class LoginScreen extends StatefulWidget { 
  const LoginScreen({super.key}); 

  @override 
  State<LoginScreen> createState() => LoginScreenState(); 
} 

class LoginScreenState extends State<LoginScreen> {
  final TextEditingController usernameController = TextEditingController();
  final TextEditingController passwordController = TextEditingController();

  void login() async {
    // Handle login logic here
    String username = usernameController.text;
    String password = passwordController.text;

    final navigator = Navigator.of(context);
    if (username == "") {
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(content: Text('Please type your username')),
      );
    }
    else if (password == '') {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Please type your password')),
        );
    }
    else if (username == 'admin' && password == '1') {
      SharedPreferences preferences = await SharedPreferences.getInstance();
      preferences.setBool('isLoggedIn', true);
      navigator.pushReplacement(
        MaterialPageRoute(builder: (context) => const HomeScreen()) 
      );
    } else {
      // Display an error message
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(content: Text('Invalid username or password')),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Login'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            TextField(
              controller: usernameController,
              decoration: const InputDecoration(
                labelText: 'Email',
                border: OutlineInputBorder(),
              ),
              keyboardType: TextInputType.emailAddress,
            ),
            const SizedBox(height: 20),
            TextField(
              controller: passwordController,
              decoration: const InputDecoration(
                labelText: 'Password',
                border: OutlineInputBorder(),
              ),
              obscureText: true,
            ),
            const SizedBox(height: 20),
            ElevatedButton(
              onPressed: () {
                login();
              },
              child: const Text('Login'),
            ),
          ],
        ),
      ),
    );
  }
}