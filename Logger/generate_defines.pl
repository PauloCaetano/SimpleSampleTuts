use strict;

my @methods = ("Critical", "Debug", "Error", "Fatal", "Information", "Notice", "Trace", "Warning");

sub Teste
{
    my @vals = @_;
    
    foreach my $val (@vals)
    {
        print $val . "\n";
    }
}

sub MSVCGenerateLoggerVar
{
    my @meth = @_;
    
    foreach my $m (@meth)
    {
        my $uc_m = uc($m);
        print "#define PCLIB_LOGGER_" . $uc_m . "_VAR(var, msg) (var)." . $m . "<LoggerImplementation>((msg), __LINE__)\n";
    }
}

sub MSVCGenerateNoLoggerVar
{
    my @meth = @_;
    
    foreach my $m (@meth)
    {
        my $uc_m = uc($m);
        print "#define PCLIB_LOGGER_" . $uc_m . "_VAR(var, msg) (var)." . $m . "((msg), __LINE__)\n";
    }
}

sub MSVCGenerateLoggerCheckVar
{
    my @meth = @_;
    
    foreach my $m (@meth)
    {
        my $uc_m = uc($m);
        print "#define PCLIB_LOGGER_" . $uc_m . "_CHECK_VAR(var, msg) \\\n";
        print "    if ((var).Is" . $m . "()) (var)." . $m . "<LoggerImplementation>((msg), __LINE__); else (void) 0\n";
    }
}

sub MSVCGenerateNoLoggerCheckVar
{
    my @meth = @_;
    
    foreach my $m (@meth)
    {
        my $uc_m = uc($m);
        print "#define PCLIB_LOGGER_" . $uc_m . "_CHECK_VAR(var, msg)\n";
    }
}

sub GCCGenerateLoggerVar
{
    my @meth = @_;
    
    foreach my $m (@meth)
    {
        my $uc_m = uc($m);
        print "#define PCLIB_LOGGER_" . $uc_m . "_VAR(var, msg) (var)." . $m . "((msg), __LINE__)\n";
    }
}

sub GCCGenerateLoggerCheckVar
{
    my @meth = @_;
    
    foreach my $m (@meth)
    {
        my $uc_m = uc($m);
        print "#define PCLIB_LOGGER_" . $uc_m . "_CHECK_VAR(var, msg) \\\n";
        print "    if ((var).Is" . $m . "()) (var)." . $m . "((msg), __LINE__); else (void) 0\n";
    }
}

sub GenerateLogger
{
    my @meth = @_;
    
    foreach my $m (@meth)
    {
        my $uc_m = uc($m);
        print "#define PCLIB_LOGGER_" . $uc_m . "(msg) PCLIB_LOGGER_" . $uc_m . "_VAR(PC_LIBLOGGER_PC, (msg))\n";
    }
}

sub GenerateLoggerCheck
{
    my @meth = @_;
    
    foreach my $m (@meth)
    {
        my $uc_m = uc($m);
        print "#define PCLIB_LOGGER_" . $uc_m . "_CHECK(msg) PCLIB_LOGGER_" . $uc_m . "_CHECK_VAR(PC_LIBLOGGER_PC, (msg))\n";
    }
}



MSVCGenerateLoggerVar(@methods);
print "\n######################\n\n";
MSVCGenerateNoLoggerVar(@methods);
print "\n######################\n\n";
MSVCGenerateLoggerCheckVar(@methods);
print "\n######################\n\n";
MSVCGenerateNoLoggerCheckVar(@methods);
print "\n######################\n\n";
GCCGenerateLoggerVar(@methods);
print "\n######################\n\n";
GCCGenerateLoggerCheckVar(@methods);
print "\n######################\n\n";
GenerateLogger(@methods);
print "\n######################\n\n";
GenerateLoggerCheck(@methods);








