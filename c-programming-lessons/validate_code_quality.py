#!/usr/bin/env python3
"""
C Programming Lessons Code Quality Validator
Validates code quality and best practices adherence across all lessons
"""

import os
import re
import sys
from pathlib import Path
from typing import List, Dict, Tuple

class CodeQualityValidator:
    def __init__(self):
        self.issues = []
        self.warnings = []
        self.total_files = 0
        self.passed_files = 0
        
    def validate_all_lessons(self) -> bool:
        """Validate all lessons in the project"""
        print("=" * 50)
        print("C Programming Lessons Code Quality Validator")
        print("=" * 50)
        
        difficulty_levels = ['basics', 'intermediate', 'pro', 'master']
        
        for level in difficulty_levels:
            if os.path.exists(level):
                print(f"\nValidating {level} level lessons...")
                print("-" * 40)
                self._validate_difficulty_level(level)
        
        self._print_summary()
        return len(self.issues) == 0
    
    def _validate_difficulty_level(self, level: str):
        """Validate all lessons in a difficulty level"""
        level_path = Path(level)
        
        for lesson_dir in sorted(level_path.glob('lesson-*')):
            if lesson_dir.is_dir():
                self._validate_lesson(lesson_dir)
    
    def _validate_lesson(self, lesson_path: Path):
        """Validate a single lesson"""
        print(f"Validating {lesson_path}...")
        
        # Check required files exist
        required_files = ['main.c', 'Makefile', 'README.md']
        for file_name in required_files:
            file_path = lesson_path / file_name
            if not file_path.exists():
                self.issues.append(f"{lesson_path}: Missing required file {file_name}")
                return
        
        # Validate C source files
        for c_file in lesson_path.glob('*.c'):
            self._validate_c_file(c_file)
        
        # Validate header files
        for h_file in lesson_path.glob('*.h'):
            self._validate_header_file(h_file)
        
        # Validate Makefile
        self._validate_makefile(lesson_path / 'Makefile')
        
        # Validate README
        self._validate_readme(lesson_path / 'README.md')
    
    def _validate_c_file(self, file_path: Path):
        """Validate C source file for best practices"""
        self.total_files += 1
        file_issues = []
        
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
                lines = content.split('\n')
        except Exception as e:
            self.issues.append(f"{file_path}: Cannot read file - {e}")
            return
        
        # Check for basic structure
        if '#include' not in content:
            file_issues.append("No #include statements found")
        
        if 'int main(' not in content and 'void main(' not in content:
            # Allow files without main (like module files)
            pass
        
        # Check for proper indentation (should use spaces, not tabs)
        for i, line in enumerate(lines, 1):
            if '\t' in line:
                file_issues.append(f"Line {i}: Uses tabs instead of spaces for indentation")
        
        # Check for proper function formatting
        function_pattern = r'^\w+\s+\w+\s*\([^)]*\)\s*\{'
        for i, line in enumerate(lines, 1):
            if re.match(function_pattern, line.strip()):
                if not line.strip().endswith('{'):
                    file_issues.append(f"Line {i}: Opening brace should be on same line as function")
        
        # Check for proper variable naming (snake_case)
        variable_pattern = r'\b[a-z][a-z0-9_]*\b'
        
        # Check for memory management (if malloc is used, free should be present)
        if 'malloc(' in content or 'calloc(' in content or 'realloc(' in content:
            if 'free(' not in content:
                file_issues.append("Memory allocation found but no corresponding free()")
        
        # Check for return statement in main
        if 'int main(' in content:
            if 'return' not in content:
                file_issues.append("main() function should have return statement")
        
        # Check for proper error handling with file operations
        if any(func in content for func in ['fopen(', 'fread(', 'fwrite(']):
            if 'NULL' not in content:
                self.warnings.append(f"{file_path}: File operations should check for NULL returns")
        
        if file_issues:
            for issue in file_issues:
                self.issues.append(f"{file_path}: {issue}")
        else:
            self.passed_files += 1
    
    def _validate_header_file(self, file_path: Path):
        """Validate header file for best practices"""
        self.total_files += 1
        file_issues = []
        
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
        except Exception as e:
            self.issues.append(f"{file_path}: Cannot read file - {e}")
            return
        
        # Check for header guards
        header_guard_pattern = r'#ifndef\s+\w+_H\s*\n#define\s+\w+_H'
        if not re.search(header_guard_pattern, content):
            file_issues.append("Missing proper header guards")
        
        # Check for #endif at end
        if not content.strip().endswith('#endif'):
            file_issues.append("Missing #endif at end of header file")
        
        if file_issues:
            for issue in file_issues:
                self.issues.append(f"{file_path}: {issue}")
        else:
            self.passed_files += 1
    
    def _validate_makefile(self, file_path: Path):
        """Validate Makefile for best practices"""
        self.total_files += 1
        file_issues = []
        
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
        except Exception as e:
            self.issues.append(f"{file_path}: Cannot read file - {e}")
            return
        
        # Check for required targets
        required_targets = ['all:', 'clean:']
        for target in required_targets:
            if target not in content:
                file_issues.append(f"Missing required target: {target}")
        
        # Check for compiler flags
        if 'CFLAGS' not in content:
            self.warnings.append(f"{file_path}: Consider defining CFLAGS for consistent compilation")
        
        if file_issues:
            for issue in file_issues:
                self.issues.append(f"{file_path}: {issue}")
        else:
            self.passed_files += 1
    
    def _validate_readme(self, file_path: Path):
        """Validate README file for completeness"""
        self.total_files += 1
        file_issues = []
        
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
        except Exception as e:
            self.issues.append(f"{file_path}: Cannot read file - {e}")
            return
        
        # Check for required sections
        required_sections = ['#', '##']  # At least some headers
        if not any(section in content for section in required_sections):
            file_issues.append("README should have proper markdown headers")
        
        # Check for code examples
        if '```c' not in content and '```' not in content:
            self.warnings.append(f"{file_path}: Consider adding code examples in README")
        
        # Check minimum length
        if len(content) < 200:
            file_issues.append("README seems too short, should provide comprehensive documentation")
        
        if file_issues:
            for issue in file_issues:
                self.issues.append(f"{file_path}: {issue}")
        else:
            self.passed_files += 1
    
    def _print_summary(self):
        """Print validation summary"""
        print("\n" + "=" * 50)
        print("VALIDATION SUMMARY")
        print("=" * 50)
        print(f"Total files validated: {self.total_files}")
        print(f"Files passed: {self.passed_files}")
        print(f"Files with issues: {len(self.issues)}")
        print(f"Warnings: {len(self.warnings)}")
        
        if self.issues:
            print("\nISSUES FOUND:")
            print("-" * 20)
            for issue in self.issues:
                print(f"❌ {issue}")
        
        if self.warnings:
            print("\nWARNINGS:")
            print("-" * 20)
            for warning in self.warnings:
                print(f"⚠️  {warning}")
        
        if not self.issues:
            print("\n✅ All code quality checks passed!")
        else:
            print(f"\n❌ Found {len(self.issues)} issues that need to be addressed.")

def main():
    """Main function"""
    validator = CodeQualityValidator()
    success = validator.validate_all_lessons()
    
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()