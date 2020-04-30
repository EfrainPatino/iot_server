const user_credentials = 'efrain';
const password_credentials = '123456';

const isAuth = (req, res, next) => {
    const {user, password, espID} = req.body;
    if (user == user_credentials && password == password_credentials) {
        console.log('Credenciales aprobadas');
        next();
    }
    else {
        console.log('Credenciales erroneas');
    }
}

module.exports = { isAuth };