document.addEventListener('DOMContentLoaded', () => {
    const usernameInput = document.getElementById('username');
    const passwordInput = document.getElementById('password');
    const loginBtn = document.getElementById('loginBtn');

    // Prevent default form submission and handle login
    loginBtn.addEventListener('click', (e) => {
        e.preventDefault();

        const username = usernameInput.value.trim();
        const password = passwordInput.value.trim();

        if (!username || !password) {
            alert("Please enter both username and password!");
            return;
        }

        // For demonstration, just show the values
        alert(`Username: ${username}\nPassword: ${password}`);

        // Here you can add logic to send data to backend or Electron main process
    });
});
