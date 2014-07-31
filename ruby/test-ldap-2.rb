require 'rubygems'
require 'net/ldap'

ldap = Net::LDAP.new :host => "mamba.cs.pub.ro",
     :port => 62136,
     :auth => {
           :method => :simple,
           :username => "cn=admin,dc=garm,dc=cs,dc=pub,dc=ro",
           :password => "xxxxxx"
     }

ldap.encryption(:simple_tls)
ldap.open do |ldap1|
	result = ldap.bind(:method => :simple, :username => "uid=gandalf,ou=WhiteCouncil,dc=garm,dc=cs,dc=pub,dc=ro", :password => "gandalf")
	if result
		puts "OK"
	else
		puts "Not OK"
	end
end
