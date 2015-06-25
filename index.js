var express      = require('express'),
    passport     = require('passport'),
    bodyParser   = require('body-parser'),
    LdapStrategy = require('passport-ldapauth');

var OPTS = {};
OPTS = {
  server: {
    url: 'ldap://ldap.forumsys.com:389',
    bindDn: 'cn=read-only-admin,dc=example,dc=com',
    bindCredentials: 'password',
    searchBase: 'dc=example,dc=com',
    searchFilter: '(uid={{username}})'
  }
};

/*
var LdapAuth = require('ldapauth-fork');
var ldap = new LdapAuth({
  url: OPTS.server.url,
  bindDn: OPTS.server.bindDn,
  bindCredentials: OPTS.server.bindCredentials,
  searchBase: OPTS.server.searchBase,
  searchFilter: OPTS.server.searchFilter,
  //log4js: require('log4js'),
  CACHE: true
});
*/

var app = express();

passport.use(new LdapStrategy(OPTS, function(user, done){
  done(null, user);
}));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: false}));
app.use(passport.initialize());

app.post('/login', passport.authenticate('ldapauth', {session: false}), function(req, res) {
  res.send({status: 'Hello ' + req.user.uid});
});
app.listen(3001);
