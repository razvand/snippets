require 'rubygems'
require 'net/ldap'

ldap = Net::LDAP.new :host => "ldap.grid.pub.ro",
     :port => 636,
     :auth => {
           :method => :simple,
           :username => "cn=admin,dc=garm,dc=cs,dc=pub,dc=ro",
           :password => "xxxxxx"
     }

ldap.encryption(:simple_tls)

result = ldap.bind_as(:base => "dc=garm,dc=cs,dc=pub,dc=ro",
	     :filter => "(uid=gandalf)",
		:password => "gandalf")

if result
	puts "OK"
else
	puts "Not OK"
end
