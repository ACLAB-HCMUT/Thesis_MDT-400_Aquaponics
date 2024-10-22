import 'package:flutter/material.dart'; 
import 'package:shared_preferences/shared_preferences.dart';

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
    if (username == 'username@example.com' && password == 'password123') {
      SharedPreferences preferences = await SharedPreferences.getInstance();
      preferences.setBool('isLoggedIn', true)

      Navigator.pushReplacementNamed(context, '/home');
    } else {
      // Display an error message
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(content: Text('Invalid email or password')),
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
              },
              child: const Text('Login'),
            ),
          ],
        ),
      ),
    );
  }
}